; Auto-generated. Do not edit!


(cl:in-package disp_cv-msg)


;//! \htmlinclude multibox.msg.html

(cl:defclass <multibox> (roslisp-msg-protocol:ros-message)
  ((timestamp
    :reader timestamp
    :initarg :timestamp
    :type cl:real
    :initform 0)
   (boxes
    :reader boxes
    :initarg :boxes
    :type (cl:vector disp_cv-msg:box)
   :initform (cl:make-array 0 :element-type 'disp_cv-msg:box :initial-element (cl:make-instance 'disp_cv-msg:box))))
)

(cl:defclass multibox (<multibox>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <multibox>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'multibox)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name disp_cv-msg:<multibox> is deprecated: use disp_cv-msg:multibox instead.")))

(cl:ensure-generic-function 'timestamp-val :lambda-list '(m))
(cl:defmethod timestamp-val ((m <multibox>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader disp_cv-msg:timestamp-val is deprecated.  Use disp_cv-msg:timestamp instead.")
  (timestamp m))

(cl:ensure-generic-function 'boxes-val :lambda-list '(m))
(cl:defmethod boxes-val ((m <multibox>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader disp_cv-msg:boxes-val is deprecated.  Use disp_cv-msg:boxes instead.")
  (boxes m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <multibox>) ostream)
  "Serializes a message object of type '<multibox>"
  (cl:let ((__sec (cl:floor (cl:slot-value msg 'timestamp)))
        (__nsec (cl:round (cl:* 1e9 (cl:- (cl:slot-value msg 'timestamp) (cl:floor (cl:slot-value msg 'timestamp)))))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 0) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __nsec) ostream))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'boxes))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'boxes))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <multibox>) istream)
  "Deserializes a message object of type '<multibox>"
    (cl:let ((__sec 0) (__nsec 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 0) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __nsec) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'timestamp) (cl:+ (cl:coerce __sec 'cl:double-float) (cl:/ __nsec 1e9))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'boxes) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'boxes)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'disp_cv-msg:box))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<multibox>)))
  "Returns string type for a message object of type '<multibox>"
  "disp_cv/multibox")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'multibox)))
  "Returns string type for a message object of type 'multibox"
  "disp_cv/multibox")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<multibox>)))
  "Returns md5sum for a message object of type '<multibox>"
  "4948510b7a7cae5de3b73ed3d60baa3b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'multibox)))
  "Returns md5sum for a message object of type 'multibox"
  "4948510b7a7cae5de3b73ed3d60baa3b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<multibox>)))
  "Returns full string definition for message of type '<multibox>"
  (cl:format cl:nil "time timestamp~%box[] boxes~%~%================================================================================~%MSG: disp_cv/box~%int32 x~%int32 y~%int32 h~%int32 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'multibox)))
  "Returns full string definition for message of type 'multibox"
  (cl:format cl:nil "time timestamp~%box[] boxes~%~%================================================================================~%MSG: disp_cv/box~%int32 x~%int32 y~%int32 h~%int32 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <multibox>))
  (cl:+ 0
     8
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'boxes) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <multibox>))
  "Converts a ROS message object to a list"
  (cl:list 'multibox
    (cl:cons ':timestamp (timestamp msg))
    (cl:cons ':boxes (boxes msg))
))
