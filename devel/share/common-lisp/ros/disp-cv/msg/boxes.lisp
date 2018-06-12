; Auto-generated. Do not edit!


(cl:in-package disp-cv-msg)


;//! \htmlinclude boxes.msg.html

(cl:defclass <boxes> (roslisp-msg-protocol:ros-message)
  ((boxes
    :reader boxes
    :initarg :boxes
    :type (cl:vector cl:integer)
   :initform (cl:make-array 0 :element-type 'cl:integer :initial-element 0)))
)

(cl:defclass boxes (<boxes>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <boxes>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'boxes)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name disp-cv-msg:<boxes> is deprecated: use disp-cv-msg:boxes instead.")))

(cl:ensure-generic-function 'boxes-val :lambda-list '(m))
(cl:defmethod boxes-val ((m <boxes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader disp-cv-msg:boxes-val is deprecated.  Use disp-cv-msg:boxes instead.")
  (boxes m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <boxes>) ostream)
  "Serializes a message object of type '<boxes>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'boxes))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    ))
   (cl:slot-value msg 'boxes))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <boxes>) istream)
  "Deserializes a message object of type '<boxes>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'boxes) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'boxes)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616)))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<boxes>)))
  "Returns string type for a message object of type '<boxes>"
  "disp-cv/boxes")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'boxes)))
  "Returns string type for a message object of type 'boxes"
  "disp-cv/boxes")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<boxes>)))
  "Returns md5sum for a message object of type '<boxes>"
  "8e8557e2ff1ec2810133dc2374d362e1")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'boxes)))
  "Returns md5sum for a message object of type 'boxes"
  "8e8557e2ff1ec2810133dc2374d362e1")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<boxes>)))
  "Returns full string definition for message of type '<boxes>"
  (cl:format cl:nil "int64[] boxes~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'boxes)))
  "Returns full string definition for message of type 'boxes"
  (cl:format cl:nil "int64[] boxes~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <boxes>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'boxes) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <boxes>))
  "Converts a ROS message object to a list"
  (cl:list 'boxes
    (cl:cons ':boxes (boxes msg))
))
