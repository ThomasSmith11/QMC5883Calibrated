import UIKit
import CoreLocation

class ViewController: UIViewController, CLLocationManagerDelegate {

    let samplesPerSecond = 100
    
    @IBOutlet weak var startButton: UIButton!

    let locationManager = CLLocationManager()
    var isSendingData = false
    var timer: Timer?

    override func viewDidLoad() {
        super.viewDidLoad()
        locationManager.delegate = self
        locationManager.startUpdatingHeading()
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
        startButton.setTitle("Stop", for: .normal)
        // Start timer to send compass heading every 200ms
        timer = Timer.scheduledTimer(timeInterval: 1/samplesPerSecond, target: self, selector: #selector(sendCompassHeading), userInfo: nil, repeats: true)
    }

    func stopSendingData() {
        isSendingData = false
        startButton.setTitle("Start", for: .normal)
        timer?.invalidate()
        timer = nil
    }

    @objc func sendCompassHeading() {
        if let magneticHeading = locationManager.heading?.magneticHeading {
            NSLog("%f", magneticHeading)
        }
    }
}
