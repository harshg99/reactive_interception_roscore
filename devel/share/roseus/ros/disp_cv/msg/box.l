;; Auto-generated. Do not edit!


(when (boundp 'disp_cv::box)
  (if (not (find-package "DISP_CV"))
    (make-package "DISP_CV"))
  (shadow 'box (find-package "DISP_CV")))
(unless (find-package "DISP_CV::BOX")
  (make-package "DISP_CV::BOX"))

(in-package "ROS")
;;//! \htmlinclude box.msg.html


(defclass disp_cv::box
  :super ros::object
  :slots (_x _y _h _w ))

(defmethod disp_cv::box
  (:init
   (&key
    ((:x __x) 0)
    ((:y __y) 0)
    ((:h __h) 0)
    ((:w __w) 0)
    )
   (send-super :init)
   (setq _x (round __x))
   (setq _y (round __y))
   (setq _h (round __h))
   (setq _w (round __w))
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:h
   (&optional __h)
   (if __h (setq _h __h)) _h)
  (:w
   (&optional __w)
   (if __w (setq _w __w)) _w)
  (:serialization-length
   ()
   (+
    ;; int32 _x
    4
    ;; int32 _y
    4
    ;; int32 _h
    4
    ;; int32 _w
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _x
       (write-long _x s)
     ;; int32 _y
       (write-long _y s)
     ;; int32 _h
       (write-long _h s)
     ;; int32 _w
       (write-long _w s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _x
     (setq _x (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _y
     (setq _y (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _h
     (setq _h (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _w
     (setq _w (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get disp_cv::box :md5sum-) "7261f46cbfcb221fb85c4d845823bb1b")
(setf (get disp_cv::box :datatype-) "disp_cv/box")
(setf (get disp_cv::box :definition-)
      "int32 x
int32 y
int32 h
int32 w

")



(provide :disp_cv/box "7261f46cbfcb221fb85c4d845823bb1b")


