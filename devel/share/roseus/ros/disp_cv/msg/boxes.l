;; Auto-generated. Do not edit!


(when (boundp 'disp_cv::boxes)
  (if (not (find-package "DISP_CV"))
    (make-package "DISP_CV"))
  (shadow 'boxes (find-package "DISP_CV")))
(unless (find-package "DISP_CV::BOXES")
  (make-package "DISP_CV::BOXES"))

(in-package "ROS")
;;//! \htmlinclude boxes.msg.html


(defclass disp_cv::boxes
  :super ros::object
  :slots (_boxes ))

(defmethod disp_cv::boxes
  (:init
   (&key
    ((:boxes __boxes) (make-array 0 :initial-element 0 :element-type :integer))
    )
   (send-super :init)
   (setq _boxes __boxes)
   self)
  (:boxes
   (&optional __boxes)
   (if __boxes (setq _boxes __boxes)) _boxes)
  (:serialization-length
   ()
   (+
    ;; int64[] _boxes
    (* 8    (length _boxes)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int64[] _boxes
     (write-long (length _boxes) s)
     (dotimes (i (length _boxes))
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke (elt _boxes i) (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class (elt _boxes i)) (= (length ((elt _boxes i) . bv)) 2)) ;; bignum
              (write-long (ash (elt ((elt _boxes i) . bv) 0) 0) s)
              (write-long (ash (elt ((elt _boxes i) . bv) 1) -1) s))
             ((and (class (elt _boxes i)) (= (length ((elt _boxes i) . bv)) 1)) ;; big1
              (write-long (elt ((elt _boxes i) . bv) 0) s)
              (write-long (if (>= (elt _boxes i) 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long (elt _boxes i) s)(write-long (if (>= (elt _boxes i) 0) 0 #xffffffff) s)))
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int64[] _boxes
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _boxes (instantiate integer-vector n))
     (dotimes (i n)
#+(or :alpha :irix6 :x86_64)
      (setf (elt _boxes i) (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf (elt _boxes i) (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
     ))
   ;;
   self)
  )

(setf (get disp_cv::boxes :md5sum-) "8e8557e2ff1ec2810133dc2374d362e1")
(setf (get disp_cv::boxes :datatype-) "disp_cv/boxes")
(setf (get disp_cv::boxes :definition-)
      "int64[] boxes

")



(provide :disp_cv/boxes "8e8557e2ff1ec2810133dc2374d362e1")


