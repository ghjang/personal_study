import Foundation
import UIKit
import MobileCoreServices


class ImagePickerHandler: NSObject
{
    typealias PickedImageHandler = ((_ pickedImage: UIImage?) -> Void)
    typealias PickedMovieHandler = ((_ pickedMovieUrl: NSURL?) -> Void)

    static let shared = ImagePickerHandler()
    
    fileprivate var m_viewCtrl: UIViewController?
    fileprivate var m_pickedImageHandler: PickedImageHandler?
    fileprivate var m_pickedMovieHandler: PickedMovieHandler?

    func selectPhoto(presentor viewCtrl: UIViewController,
                     from srcType: UIImagePickerControllerSourceType,
                     completion handler: PickedImageHandler? = nil)
    {
        if !UIImagePickerController.isSourceTypeAvailable(srcType) {
            return
        }
        
        self.m_viewCtrl = viewCtrl
        self.m_pickedImageHandler = handler
        
        let pickerCtrl = UIImagePickerController()
        pickerCtrl.delegate = self;
        pickerCtrl.sourceType = srcType
        pickerCtrl.allowsEditing = false
        pickerCtrl.mediaTypes = [kUTTypeImage as String]
        
        viewCtrl.present(pickerCtrl, animated: true)
    }

    func selectMovie(presentor viewCtrl: UIViewController,
                     from srcType: UIImagePickerControllerSourceType,
                     completion handler: PickedMovieHandler? = nil)
    {
        if !UIImagePickerController.isSourceTypeAvailable(srcType) {
            return
        }
        
        self.m_viewCtrl = viewCtrl
        self.m_pickedMovieHandler = handler
        
        let pickerCtrl = UIImagePickerController()
        pickerCtrl.delegate = self;
        pickerCtrl.sourceType = srcType
        pickerCtrl.allowsEditing = false
        pickerCtrl.mediaTypes = [kUTTypeMovie as String]
        
        viewCtrl.present(pickerCtrl, animated: true)
    }

}


extension ImagePickerHandler: UIImagePickerControllerDelegate, UINavigationControllerDelegate
{
    
    func imagePickerControllerDidCancel(_ picker: UIImagePickerController)
    {
        self.m_viewCtrl?.dismiss(animated: true)
        
        self.m_viewCtrl = nil
        self.m_pickedImageHandler = nil
        self.m_pickedMovieHandler = nil
    }
    
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [String : Any])
    {
        #if DEBUG
            if let mediaType = info[UIImagePickerControllerMediaType] as? String {
                print("mediaType=\(mediaType.debugDescription)")
            }
        #endif // DEBUG
        
        if let img = info[UIImagePickerControllerOriginalImage] as? UIImage {
            self.m_pickedImageHandler?(img)
        }
        else if let url = info[UIImagePickerControllerMediaURL] as? NSURL {
            self.m_pickedMovieHandler?(url)
        }
        else {
            print("something went wrong while picking an item from the photo library.")
            self.m_pickedImageHandler?(nil)
            self.m_pickedMovieHandler?(nil)
        }
        self.m_viewCtrl?.dismiss(animated: true)
        
        self.m_viewCtrl = nil
        self.m_pickedImageHandler = nil
        self.m_pickedMovieHandler = nil
    }
    
}
