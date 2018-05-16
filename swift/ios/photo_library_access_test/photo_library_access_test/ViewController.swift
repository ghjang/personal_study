//
//  ViewController.swift
//  photo_library_access_test
//
//  Created by Gil Ho Jang on 17/05/2018.
//  Copyright © 2018 Gil Ho Jang. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet var m_photoImageView: UIImageView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
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
        
        PhotoSelector.shared.select(presentor: self,
                                    from: .photoLibrary,
                                    completion: {
                                        (pickedImageUrl) in
                                            if let imgData = NSData(contentsOf: pickedImageUrl as URL) {
                                                self.m_photoImageView.image = UIImage(data: imgData as Data)
                                            }
                                    })
    }
    
}
