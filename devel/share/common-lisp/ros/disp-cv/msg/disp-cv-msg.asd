
(cl:in-package :asdf)

(defsystem "disp-cv-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "boxes" :depends-on ("_package_boxes"))
    (:file "_package_boxes" :depends-on ("_package"))
  ))