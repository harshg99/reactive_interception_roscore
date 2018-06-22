;; Auto-generated. Do not edit!


(when (boundp 'disp_cv::reg_pos3Dtime)
  (if (not (find-package "DISP_CV"))
    (make-package "DISP_CV"))
  (shadow 'reg_pos3Dtime (find-package "DISP_CV")))
(unless (find-package "DISP_CV::REG_POS3DTIME")
  (make-package "DISP_CV::REG_POS3DTIME"))

(in-package "ROS")
;;//! \htmlinclude reg_pos3Dtime.msg.html


(defclass disp_cv::reg_pos3Dtime
  :super ros::object
  :slots (_points _ref ))

(defmethod disp_cv::reg_pos3Dtime
  (:init
   (&key
    ((:points __points) (let (r) (dotimes (i 0) (push (instance disp_cv::pos3dtime :init) r)) r))
    ((:ref __ref) 0)
    )
   (send-super :init)
   (setq _points __points)
   (setq _ref (round __ref))
   self)
  (:points
   (&rest __points)
   (if (keywordp (car __points))
       (send* _points __points)
     (progn
       (if __points (setq _points (car __points)))
       _points)))
  (:ref
   (&optional __ref)
   (if __ref (setq _ref __ref)) _ref)
  (:serialization-length
   ()
   (+
    ;; disp_cv/pos3dtime[] _points
    (apply #'+ (send-all _points :serialization-length)) 4
    ;; int16 _ref
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; disp_cv/pos3dtime[] _points
     (write-long (length _points) s)
     (dolist (elem _points)
       (send elem :serialize s)
       )
     ;; int16 _ref
       (write-word _ref s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; disp_cv/pos3dtime[] _points
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _points (let (r) (dotimes (i n) (push (instance disp_cv::pos3dtime :init) r)) r))
     (dolist (elem- _points)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; int16 _ref
     (setq _ref (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get disp_cv::reg_pos3Dtime :md5sum-) "e34d86389e60cf5269d611c175e16534")
(setf (get disp_cv::reg_pos3Dtime :datatype-) "disp_cv/reg_pos3Dtime")
(setf (get disp_cv::reg_pos3Dtime :definition-)
      "pos3dtime[] points
int16 ref

================================================================================
MSG: disp_cv/pos3dtime
time timestamp
float64 x
float64 y
float64 z

")



(provide :disp_cv/reg_pos3Dtime "e34d86389e60cf5269d611c175e16534")


