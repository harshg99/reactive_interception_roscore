
(cl:in-package :asdf)

(defsystem "disp_cv-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "box" :depends-on ("_package_box"))
    (:file "_package_box" :depends-on ("_package"))
    (:file "multibox" :depends-on ("_package_multibox"))
    (:file "_package_multibox" :depends-on ("_package"))
  ))