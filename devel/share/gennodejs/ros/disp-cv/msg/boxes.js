// Auto-generated. Do not edit!

// (in-package disp-cv.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class boxes {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.boxes = null;
    }
    else {
      if (initObj.hasOwnProperty('boxes')) {
        this.boxes = initObj.boxes
      }
      else {
        this.boxes = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type boxes
    // Serialize message field [boxes]
    bufferOffset = _arraySerializer.int64(obj.boxes, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type boxes
    let len;
    let data = new boxes(null);
    // Deserialize message field [boxes]
    data.boxes = _arrayDeserializer.int64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.boxes.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'disp-cv/boxes';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8e8557e2ff1ec2810133dc2374d362e1';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int64[] boxes
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new boxes(null);
    if (msg.boxes !== undefined) {
      resolved.boxes = msg.boxes;
    }
    else {
      resolved.boxes = []
    }

    return resolved;
    }
};

module.exports = boxes;
