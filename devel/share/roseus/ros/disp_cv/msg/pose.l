;; Auto-generated. Do not edit!


(when (boundp 'disp_cv::pose)
  (if (not (find-package "DISP_CV"))
    (make-package "DISP_CV"))
  (shadow 'pose (find-package "DISP_CV")))
(unless (find-package "DISP_CV::POSE")
  (make-package "DISP_CV::POSE"))

(in-package "ROS")
;;//! \htmlinclude pose.msg.html


(defclass disp_cv::pose
  :super ros::object
  :slots (_x _y _z _r1 _r2 _r3 ))

(defmethod disp_cv::pose
  (:init
   (&key
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:z __z) 0.0)
    ((:r1 __r1) 0.0)
    ((:r2 __r2) 0.0)
    ((:r3 __r3) 0.0)
    )
   (send-super :init)
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _z (float __z))
   (setq _r1 (float __r1))
   (setq _r2 (float __r2))
   (setq _r3 (float __r3))
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:z
   (&optional __z)
   (if __z (setq _z __z)) _z)
  (:r1
   (&optional __r1)
   (if __r1 (setq _r1 __r1)) _r1)
  (:r2
   (&optional __r2)
   (if __r2 (setq _r2 __r2)) _r2)
  (:r3
   (&optional __r3)
   (if __r3 (setq _r3 __r3)) _r3)
  (:serialization-length
   ()
   (+
    ;; float64 _x
    8
    ;; float64 _y
    8
    ;; float64 _z
    8
    ;; float64 _r1
    8
    ;; float64 _r2
    8
    ;; float64 _r3
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _x
       (sys::poke _x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y
       (sys::poke _y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _z
       (sys::poke _z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _r1
       (sys::poke _r1 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _r2
       (sys::poke _r2 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _r3
       (sys::poke _r3 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _x
     (setq _x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y
     (setq _y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _z
     (setq _z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _r1
     (setq _r1 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _r2
     (setq _r2 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _r3
     (setq _r3 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get disp_cv::pose :md5sum-) "a916e8e6b6d6e7ed2d34b11e5cf97f25")
(setf (get disp_cv::pose :datatype-) "disp_cv/pose")
(setf (get disp_cv::pose :definition-)
      "float64 x
float64 y
float64 z
float64 r1
float64 r2
float64 r3

")



(provide :disp_cv/pose "a916e8e6b6d6e7ed2d34b11e5cf97f25")


