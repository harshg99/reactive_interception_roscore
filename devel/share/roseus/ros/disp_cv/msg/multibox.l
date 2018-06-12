;; Auto-generated. Do not edit!


(when (boundp 'disp_cv::multibox)
  (if (not (find-package "DISP_CV"))
    (make-package "DISP_CV"))
  (shadow 'multibox (find-package "DISP_CV")))
(unless (find-package "DISP_CV::MULTIBOX")
  (make-package "DISP_CV::MULTIBOX"))

(in-package "ROS")
;;//! \htmlinclude multibox.msg.html


(defclass disp_cv::multibox
  :super ros::object
  :slots (_timestamp _boxes ))

(defmethod disp_cv::multibox
  (:init
   (&key
    ((:timestamp __timestamp) (instance ros::time :init))
    ((:boxes __boxes) (let (r) (dotimes (i 0) (push (instance disp_cv::box :init) r)) r))
    )
   (send-super :init)
   (setq _timestamp __timestamp)
   (setq _boxes __boxes)
   self)
  (:timestamp
   (&optional __timestamp)
   (if __timestamp (setq _timestamp __timestamp)) _timestamp)
  (:boxes
   (&rest __boxes)
   (if (keywordp (car __boxes))
       (send* _boxes __boxes)
     (progn
       (if __boxes (setq _boxes (car __boxes)))
       _boxes)))
  (:serialization-length
   ()
   (+
    ;; time _timestamp
    8
    ;; disp_cv/box[] _boxes
    (apply #'+ (send-all _boxes :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; time _timestamp
       (write-long (send _timestamp :sec) s) (write-long (send _timestamp :nsec) s)
     ;; disp_cv/box[] _boxes
     (write-long (length _boxes) s)
     (dolist (elem _boxes)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; time _timestamp
     (send _timestamp :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _timestamp :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; disp_cv/box[] _boxes
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _boxes (let (r) (dotimes (i n) (push (instance disp_cv::box :init) r)) r))
     (dolist (elem- _boxes)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get disp_cv::multibox :md5sum-) "4948510b7a7cae5de3b73ed3d60baa3b")
(setf (get disp_cv::multibox :datatype-) "disp_cv/multibox")
(setf (get disp_cv::multibox :definition-)
      "time timestamp
box[] boxes

================================================================================
MSG: disp_cv/box
int32 x
int32 y
int32 h
int32 w

")



(provide :disp_cv/multibox "4948510b7a7cae5de3b73ed3d60baa3b")


