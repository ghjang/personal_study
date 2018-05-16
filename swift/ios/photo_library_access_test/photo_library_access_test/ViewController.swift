import UIKit
import AVKit


// NOTE: This example is for iOS 10.x and above.


class ViewController: UIViewController
{

    @IBOutlet var m_photoImageView: UIImageView!
    @IBOutlet var m_moviePlayerView: UIView!
    
    var m_avPlayer: AVPlayer?
    
    override func viewDidLoad()
    {
        super.viewDidLoad()
        
        // Do any additional setup after loading the view, typically from a nib.

        self.m_avPlayer = AVPlayer()
        let layer = AVPlayerLayer(player: self.m_avPlayer)
        layer.frame = self.m_moviePlayerView.bounds
        self.m_moviePlayerView.layer.addSublayer(layer)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    @IBAction func selectPhotoButtonTouched(_ sender: UIButton) {
        /*
        CameraHandler.shared.imagePickedBlock = {
            (image) in
                self.m_photoImageView.image = image
        }
        CameraHandler.shared.showActionSheet(vc: self)
        */
        
        ImagePickerHandler.shared.selectPhoto(presentor: self,
                                              from: .photoLibrary,
                                              completion: {
                                                (pickedImage) in
                                                    self.m_photoImageView.image = pickedImage
                                              })
    }
    
    @IBAction func selectMovieButtonTouched(_ sender: UIButton)
    {
        ImagePickerHandler.shared.selectMovie(presentor: self,
                                              from: .photoLibrary,
                                              completion: {
                                                (pickedMovieUrl) in
                                                    if let url = pickedMovieUrl {
                                                        self.m_avPlayer?.replaceCurrentItem(with: AVPlayerItem(url: url as URL))
                                                        self.m_avPlayer?.play()
                                                    }
                                              })
    }

}
