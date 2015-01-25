// y1 -127 - 128

// x2 -127 - 128
// y2 -127 - 128

var maxPower = 100;
var joyStickSize = 256;
var joyStickDeadzone = 5;

function drive(joyY1, joyX2, joyY2) {
  if (Math.abs(joyY1) < joyStickDeadzone) { joyY1 = 0; }
  if (Math.abs(joyX2) < joyStickDeadzone) { joyX2 = 0; }
  if (Math.abs(joyY2) < joyStickDeadzone) { joyY2 = 0; }

  var power = maxPower * (joyY1 / (joyStickSize / 2));
  var direction = (((Math.atan2(joyY2 , joyX2)) * (180/Math.PI)) - 90) * -1;
  
  if (direction > 90)
      direction = direction - 180;
  
  var motorLeft;
  var motorRight;
  
  if (direction == 0) {
      motorLeft = power;
      motorRight = power;
  }
  if (direction > 45) {
      motorLeft = power;
      motorRight = power * toPercent(-direction + 45, 45);
  }
  else if (direction > 0) {
      motorLeft = power;
      motorRight = power - power * toPercent(direction, 45);
  }
  else if (direction < -45) {
      motorLeft = power * toPercent(-direction - 45, 45);
      motorRight = power;
  }else if (direction < 0) {
      motorLeft = power + power * toPercent(direction, 45);
      motorRight = power;
  }
  
  // console.log("P:", power);
  // console.log("D:", direction);
  // console.log("X:", joyX2);
  // console.log("Y:", joyY2);
  // console.log("L:", motorLeft);
  // console.log("R:", motorRight);
  // console.log();
  
  // console.log(joyX2, joyY2, "   ", motorLeft, motorRight);
  log(power, direction, joyX2, joyY2, motorLeft, motorRight);
}

function toPercent(val, max) {
    return val/max;
}

var logData = "";

function log() {    
  for (var i = 0; i < arguments.length; i++)
    logData = logData.concat(arguments[i], "\n");
}

function writeToFile(data, fileName) {
    var fs = require("fs");
    
    console.log('Writing to ' + fileName + '...');
    
    fs.writeFile(fileName, data, function(err) {
      if(err) throw err;
      console.log(fileName + ' write complete!');
    });
}


// Writing data to file tests
/* var inc = 16;

var x = -128;
while (x <= 128) {
    var y = -128;
    while (y <= 128) {
        drive(128, x, y);
        y = y + inc;
    }
    
    writeToFile(logData, "data" + x + ".txt");
    x = x + inc;
}

var i = 0;
while (i <= 128) {
    drive(128, i, i);
    i = i + 1;
}

writeToFile(logData, "dataXY.txt");

*/