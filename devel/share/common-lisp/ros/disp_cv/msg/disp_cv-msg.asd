
(cl:in-package :asdf)

(defsystem "disp_cv-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "box" :depends-on ("_package_box"))
    (:file "_package_box" :depends-on ("_package"))
    (:file "multibox" :depends-on ("_package_multibox"))
    (:file "_package_multibox" :depends-on ("_package"))
    (:file "pos3dtime" :depends-on ("_package_pos3dtime"))
    (:file "_package_pos3dtime" :depends-on ("_package"))
    (:file "pose" :depends-on ("_package_pose"))
    (:file "_package_pose" :depends-on ("_package"))
    (:file "reg_pos3Dtime" :depends-on ("_package_reg_pos3Dtime"))
    (:file "_package_reg_pos3Dtime" :depends-on ("_package"))
  ))