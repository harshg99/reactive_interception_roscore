// Auto-generated. Do not edit!

// (in-package disp_cv.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let pos3dtime = require('./pos3dtime.js');

//-----------------------------------------------------------

class reg_pos3Dtime {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.points = null;
      this.ref = null;
    }
    else {
      if (initObj.hasOwnProperty('points')) {
        this.points = initObj.points
      }
      else {
        this.points = [];
      }
      if (initObj.hasOwnProperty('ref')) {
        this.ref = initObj.ref
      }
      else {
        this.ref = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type reg_pos3Dtime
    // Serialize message field [points]
    // Serialize the length for message field [points]
    bufferOffset = _serializer.uint32(obj.points.length, buffer, bufferOffset);
    obj.points.forEach((val) => {
      bufferOffset = pos3dtime.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [ref]
    bufferOffset = _serializer.int16(obj.ref, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type reg_pos3Dtime
    let len;
    let data = new reg_pos3Dtime(null);
    // Deserialize message field [points]
    // Deserialize array length for message field [points]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.points = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.points[i] = pos3dtime.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [ref]
    data.ref = _deserializer.int16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 32 * object.points.length;
    return length + 6;
  }

  static datatype() {
    // Returns string type for a message object
    return 'disp_cv/reg_pos3Dtime';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e34d86389e60cf5269d611c175e16534';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    pos3dtime[] points
    int16 ref
    
    ================================================================================
    MSG: disp_cv/pos3dtime
    time timestamp
    float64 x
    float64 y
    float64 z
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new reg_pos3Dtime(null);
    if (msg.points !== undefined) {
      resolved.points = new Array(msg.points.length);
      for (let i = 0; i < resolved.points.length; ++i) {
        resolved.points[i] = pos3dtime.Resolve(msg.points[i]);
      }
    }
    else {
      resolved.points = []
    }

    if (msg.ref !== undefined) {
      resolved.ref = msg.ref;
    }
    else {
      resolved.ref = 0
    }

    return resolved;
    }
};

module.exports = reg_pos3Dtime;
