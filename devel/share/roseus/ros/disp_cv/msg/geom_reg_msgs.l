;; Auto-generated. Do not edit!


(when (boundp 'disp_cv::geom_reg_msgs)
  (if (not (find-package "DISP_CV"))
    (make-package "DISP_CV"))
  (shadow 'geom_reg_msgs (find-package "DISP_CV")))
(unless (find-package "DISP_CV::GEOM_REG_MSGS")
  (make-package "DISP_CV::GEOM_REG_MSGS"))

(in-package "ROS")
;;//! \htmlinclude geom_reg_msgs.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass disp_cv::geom_reg_msgs
  :super ros::object
  :slots (_points ))

(defmethod disp_cv::geom_reg_msgs
  (:init
   (&key
    ((:points __points) (let (r) (dotimes (i 0) (push (instance geometry_msgs::Point :init) r)) r))
    )
   (send-super :init)
   (setq _points __points)
   self)
  (:points
   (&rest __points)
   (if (keywordp (car __points))
       (send* _points __points)
     (progn
       (if __points (setq _points (car __points)))
       _points)))
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Point[] _points
    (apply #'+ (send-all _points :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Point[] _points
     (write-long (length _points) s)
     (dolist (elem _points)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Point[] _points
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _points (let (r) (dotimes (i n) (push (instance geometry_msgs::Point :init) r)) r))
     (dolist (elem- _points)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get disp_cv::geom_reg_msgs :md5sum-) "3fb3f9dacc279b964c4c8341122c34df")
(setf (get disp_cv::geom_reg_msgs :datatype-) "disp_cv/geom_reg_msgs")
(setf (get disp_cv::geom_reg_msgs :definition-)
      "geometry_msgs/Point[] points

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :disp_cv/geom_reg_msgs "3fb3f9dacc279b964c4c8341122c34df")


