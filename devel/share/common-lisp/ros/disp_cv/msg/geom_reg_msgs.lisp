; Auto-generated. Do not edit!


(cl:in-package disp_cv-msg)


;//! \htmlinclude geom_reg_msgs.msg.html

(cl:defclass <geom_reg_msgs> (roslisp-msg-protocol:ros-message)
  ((points
    :reader points
    :initarg :points
    :type (cl:vector geometry_msgs-msg:Point)
   :initform (cl:make-array 0 :element-type 'geometry_msgs-msg:Point :initial-element (cl:make-instance 'geometry_msgs-msg:Point))))
)

(cl:defclass geom_reg_msgs (<geom_reg_msgs>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <geom_reg_msgs>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'geom_reg_msgs)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name disp_cv-msg:<geom_reg_msgs> is deprecated: use disp_cv-msg:geom_reg_msgs instead.")))

(cl:ensure-generic-function 'points-val :lambda-list '(m))
(cl:defmethod points-val ((m <geom_reg_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader disp_cv-msg:points-val is deprecated.  Use disp_cv-msg:points instead.")
  (points m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <geom_reg_msgs>) ostream)
  "Serializes a message object of type '<geom_reg_msgs>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'points))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'points))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <geom_reg_msgs>) istream)
  "Deserializes a message object of type '<geom_reg_msgs>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'points) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'points)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:Point))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<geom_reg_msgs>)))
  "Returns string type for a message object of type '<geom_reg_msgs>"
  "disp_cv/geom_reg_msgs")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'geom_reg_msgs)))
  "Returns string type for a message object of type 'geom_reg_msgs"
  "disp_cv/geom_reg_msgs")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<geom_reg_msgs>)))
  "Returns md5sum for a message object of type '<geom_reg_msgs>"
  "3fb3f9dacc279b964c4c8341122c34df")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'geom_reg_msgs)))
  "Returns md5sum for a message object of type 'geom_reg_msgs"
  "3fb3f9dacc279b964c4c8341122c34df")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<geom_reg_msgs>)))
  "Returns full string definition for message of type '<geom_reg_msgs>"
  (cl:format cl:nil "geometry_msgs/Point[] points~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'geom_reg_msgs)))
  "Returns full string definition for message of type 'geom_reg_msgs"
  (cl:format cl:nil "geometry_msgs/Point[] points~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <geom_reg_msgs>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'points) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <geom_reg_msgs>))
  "Converts a ROS message object to a list"
  (cl:list 'geom_reg_msgs
    (cl:cons ':points (points msg))
))
