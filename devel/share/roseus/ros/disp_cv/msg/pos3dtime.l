;; Auto-generated. Do not edit!


(when (boundp 'disp_cv::pos3dtime)
  (if (not (find-package "DISP_CV"))
    (make-package "DISP_CV"))
  (shadow 'pos3dtime (find-package "DISP_CV")))
(unless (find-package "DISP_CV::POS3DTIME")
  (make-package "DISP_CV::POS3DTIME"))

(in-package "ROS")
;;//! \htmlinclude pos3dtime.msg.html


(defclass disp_cv::pos3dtime
  :super ros::object
  :slots (_timestamp _x _y _z ))

(defmethod disp_cv::pos3dtime
  (:init
   (&key
    ((:timestamp __timestamp) (instance ros::time :init))
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:z __z) 0.0)
    )
   (send-super :init)
   (setq _timestamp __timestamp)
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _z (float __z))
   self)
  (:timestamp
   (&optional __timestamp)
   (if __timestamp (setq _timestamp __timestamp)) _timestamp)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:z
   (&optional __z)
   (if __z (setq _z __z)) _z)
  (:serialization-length
   ()
   (+
    ;; time _timestamp
    8
    ;; float64 _x
    8
    ;; float64 _y
    8
    ;; float64 _z
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; time _timestamp
       (write-long (send _timestamp :sec) s) (write-long (send _timestamp :nsec) s)
     ;; float64 _x
       (sys::poke _x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y
       (sys::poke _y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _z
       (sys::poke _z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; time _timestamp
     (send _timestamp :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _timestamp :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _x
     (setq _x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y
     (setq _y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _z
     (setq _z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get disp_cv::pos3dtime :md5sum-) "3b3a345dba06884a6ee42beb55ab1ae4")
(setf (get disp_cv::pos3dtime :datatype-) "disp_cv/pos3dtime")
(setf (get disp_cv::pos3dtime :definition-)
      "time timestamp
float64 x
float64 y
float64 z

")



(provide :disp_cv/pos3dtime "3b3a345dba06884a6ee42beb55ab1ae4")


