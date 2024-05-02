import UIKit
import CoreLocation

class ViewController: UIViewController, CLLocationManagerDelegate {
    
    @IBOutlet weak var headingLabel: UILabel!
    @IBOutlet weak var startButton: UIButton!

    let locationManager = CLLocationManager()
    var isSendingData = false
    var timer: Timer?

    override func viewDidLoad() {
        super.viewDidLoad()
        locationManager.delegate = self
        locationManager.startUpdatingHeading()
        locationManager.requestWhenInUseAuthorization()
    }

    @IBAction func startButtonTapped(_ sender: UIButton) {
        if isSendingData {
            stopSendingData()
        } else {
            startSendingData()
        }
    }

    func startSendingData() {
        isSendingData = true
        let attrTitle = NSAttributedString(string: "Stop", attributes: [NSAttributedString.Key.font: UIFont.systemFont(ofSize: 50)])
        startButton.setAttributedTitle(attrTitle, for: UIControl.State.normal)
        timer = Timer.scheduledTimer(timeInterval: 0.1, target: self, selector: #selector(sendCompassHeading), userInfo: nil, repeats: true)
    }

    func stopSendingData() {
        isSendingData = false
        let attrTitle = NSAttributedString(string: "Start", attributes: [NSAttributedString.Key.font: UIFont.systemFont(ofSize: 50)])
        startButton.setAttributedTitle(attrTitle, for: UIControl.State.normal)
        timer?.invalidate()
        timer = nil
    }

    @objc func sendCompassHeading() {
        guard let magneticHeading = locationManager.heading?.magneticHeading else {
            NSLog("Failed to obtain heading.")
            return
        }
        NSLog("%d", Int(magneticHeading))
        updateHeadingLabel(magneticHeading: magneticHeading)
    }

    func updateHeadingLabel(magneticHeading: CLLocationDirection) {
        headingLabel.text = "\(Int(magneticHeading))°"
    }

    func locationManager(_ manager: CLLocationManager, didUpdateHeading newHeading: CLHeading) {
        if !isSendingData {
            updateHeadingLabel(magneticHeading: newHeading.magneticHeading)
        }
    }

    func locationManager(_ manager: CLLocationManager, didFailWithError error: Error) {
        NSLog("Location manager failed with error: \(error.localizedDescription)")
    }
}
