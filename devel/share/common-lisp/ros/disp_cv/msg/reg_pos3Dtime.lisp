; Auto-generated. Do not edit!


(cl:in-package disp_cv-msg)


;//! \htmlinclude reg_pos3Dtime.msg.html

(cl:defclass <reg_pos3Dtime> (roslisp-msg-protocol:ros-message)
  ((points
    :reader points
    :initarg :points
    :type (cl:vector disp_cv-msg:pos3dtime)
   :initform (cl:make-array 0 :element-type 'disp_cv-msg:pos3dtime :initial-element (cl:make-instance 'disp_cv-msg:pos3dtime)))
   (ref
    :reader ref
    :initarg :ref
    :type cl:fixnum
    :initform 0))
)

(cl:defclass reg_pos3Dtime (<reg_pos3Dtime>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <reg_pos3Dtime>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'reg_pos3Dtime)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name disp_cv-msg:<reg_pos3Dtime> is deprecated: use disp_cv-msg:reg_pos3Dtime instead.")))

(cl:ensure-generic-function 'points-val :lambda-list '(m))
(cl:defmethod points-val ((m <reg_pos3Dtime>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader disp_cv-msg:points-val is deprecated.  Use disp_cv-msg:points instead.")
  (points m))

(cl:ensure-generic-function 'ref-val :lambda-list '(m))
(cl:defmethod ref-val ((m <reg_pos3Dtime>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader disp_cv-msg:ref-val is deprecated.  Use disp_cv-msg:ref instead.")
  (ref m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <reg_pos3Dtime>) ostream)
  "Serializes a message object of type '<reg_pos3Dtime>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'points))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'points))
  (cl:let* ((signed (cl:slot-value msg 'ref)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <reg_pos3Dtime>) istream)
  "Deserializes a message object of type '<reg_pos3Dtime>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'points) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'points)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'disp_cv-msg:pos3dtime))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'ref) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<reg_pos3Dtime>)))
  "Returns string type for a message object of type '<reg_pos3Dtime>"
  "disp_cv/reg_pos3Dtime")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'reg_pos3Dtime)))
  "Returns string type for a message object of type 'reg_pos3Dtime"
  "disp_cv/reg_pos3Dtime")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<reg_pos3Dtime>)))
  "Returns md5sum for a message object of type '<reg_pos3Dtime>"
  "e34d86389e60cf5269d611c175e16534")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'reg_pos3Dtime)))
  "Returns md5sum for a message object of type 'reg_pos3Dtime"
  "e34d86389e60cf5269d611c175e16534")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<reg_pos3Dtime>)))
  "Returns full string definition for message of type '<reg_pos3Dtime>"
  (cl:format cl:nil "pos3dtime[] points~%int16 ref~%~%================================================================================~%MSG: disp_cv/pos3dtime~%time timestamp~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'reg_pos3Dtime)))
  "Returns full string definition for message of type 'reg_pos3Dtime"
  (cl:format cl:nil "pos3dtime[] points~%int16 ref~%~%================================================================================~%MSG: disp_cv/pos3dtime~%time timestamp~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <reg_pos3Dtime>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'points) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <reg_pos3Dtime>))
  "Converts a ROS message object to a list"
  (cl:list 'reg_pos3Dtime
    (cl:cons ':points (points msg))
    (cl:cons ':ref (ref msg))
))
