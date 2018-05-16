import Foundation
import UIKit


class PhotoSelector: NSObject
{
    typealias PickedImageHandler = ((_ pickedImageUrl: NSURL) -> Void)

    static let shared = PhotoSelector()
    
    fileprivate var m_viewCtrl: UIViewController?
    fileprivate var m_pickedImageHandler: PickedImageHandler?
    
    func select(presentor viewCtrl: UIViewController,
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
        viewCtrl.present(pickerCtrl, animated: true)
    }
    
}


extension PhotoSelector: UIImagePickerControllerDelegate, UINavigationControllerDelegate
{
    
    func imagePickerControllerDidCancel(_ picker: UIImagePickerController)
    {
        self.m_viewCtrl?.dismiss(animated: true)
        
        self.m_viewCtrl = nil
    }
    
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [String : Any])
    {
        if let imgUrl = info[UIImagePickerControllerImageURL] as? NSURL {
            self.m_pickedImageHandler?(imgUrl)
        }
        else{
            print("something went wrong while picking an imag.")
        }
        self.m_viewCtrl?.dismiss(animated: true)
        
        self.m_viewCtrl = nil
        self.m_pickedImageHandler = nil
    }
    
}
