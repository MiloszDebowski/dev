// Set DEBUG to true for debugging
DEBUG = false;

// Variables for runtime object manipulation and root reference
var runtime = null; //holds the object that we need to manipulate the scene during the runtime
var root = null; //reference to our matrixTransform obj

// Variables for tracking status and initialization
var initDone = false; //false as long we haven't used the initialized the tracker
var doTracking = true; //to track or not to track

// Canvas/video size
var width = 960; 
var height = 720; 

// Canvas and video canvas objects
var canvas = null;   
var videoCanvas = null; 

// Marker detection and raster objects
var detector = null;    
var raster = null;     

// Matrix from JSARToolkit and light threshold
var resultMat = null;    
var threshold = 100;    

// Variable for video stream
var videoStream = null;  

// Create a video element
var video = document.createElement('video'); 

// Initialize video properties
video.width = width; 
video.height = height;
video.autoplay = true;
video.playsInline = true;

// Define video constraints
var constraints = null;

var totalNumberModels = 2;
 
// Check if it's a mobile device and set constraints accordingly
if(checkMobileDevice()){
    constraints = { video: { facingMode: "environment"  }, audio: false };
} else {
    constraints = { video: true, audio: false };
}

// Check if getUserMedia is supported and handle the stream
if (navigator.mediaDevices && navigator.mediaDevices.getUserMedia) {
     // Modern non-iOS Safari browsers
    navigator.mediaDevices.getUserMedia(constraints)
      .then(handleStream)
      .catch(handleError);
  } else if (navigator.getUserMedia) {
    // iOS Safari
    navigator.getUserMedia(constraints, handleStream, handleError);
  } else {
    console.log("getUserMedia is not supported in your browser");
  }

// Function to handle the stream
  function handleStream(stream) {
      
            video.crossOrigin = ""; //allow cross-domain communication

            if ("srcObject" in video) {
                video.srcObject = stream;
              } else {
                // Avoid using this in new browsers
                video.src = window.URL.createObjectURL(stream);
              }
            //videoStream = stream;  
           video.play();
  }
  
  function handleError(error) {

  }



// Function to check if the application is running on a mobile device
function checkMobileDevice(){
    var a;
   console.log(window.navigator.userAgent);
       if (navigator.userAgent.match(/Android/i)
       || navigator.userAgent.match(/webOS/i)
       || navigator.userAgent.match(/iPhone/i)
       || navigator.userAgent.match(/iPad/i)
       || navigator.userAgent.match(/iPod/i)
       || navigator.userAgent.match(/BlackBerry/i)
       || navigator.userAgent.match(/Windows Phone/i)) {
          a = true ;
       } else {
          a = false ;
       } 
     
    return a;
}


var a = true;
// The document's onload function executed when the page is fully loaded
document.onload = function() 
{
    runtime = document.getElementById("x3d").runtime; //allows to manipulate the x3dom context during the runtime

    //root = document.getElementById("root"); //get the MatrixTransform node

    runtime.exitFrame = function () {
        if (!initDone) {
            initializeTracker();
            initDone = true;
        }

        if (doTracking) {
            animate();

            this.triggerRedraw(); //triggers redraw function

            if(a){
                console.log(this);
                a= false;
            }

        }
    };
};

// Function to redraw the canvas
function redraw()  //redraw
{
    videoCanvas.getContext('2d').drawImage(video, 0, 0, 960, 720);
    canvas.getContext('2d').drawImage(videoCanvas, 0, 0, width, height);
    // Tell JSARToolKit that the canvas has changed.
    canvas.changed = true;
}

// Function to animate responsible for drawing the video frame to the canvas, detecting markers in the video frame, and updating the position and orientation of the 3D models based on the detected markers.
function animate()
{
    // Draw the video frame to the canvas.
    try {
        redraw();
    }
    catch (e) {
        // workaround for Firefox
        if (e.name == "NS_ERROR_NOT_AVAILABLE") {
            setTimeout(function() { redraw(); }, 10);
        }
        else { throw e; }
    }
    // Use the detector object to find markers in the raster object (the canvas), using the given threshold.
    var markerCount = detector.detectMarkerLite(raster, threshold);
    var nMarkerArray = []; // Array to store nMarker values

    //If there are no markers all the 3D models will be hided
  if (!markerCount) {
      for (var i = 0; i <= totalNumberModels; i++) {
          document.getElementById("switcher" + i).setAttribute("whichChoice", -1);
      }
  }

    // For each detected marker...
    for (var i=0; i<markerCount; i++) {

        console.log("MARKER");
        
        //Obtaining the marker number 
        var numberMarker = detector.getIdMarkerData(i);
        var nMarker = numberMarker._packet[1];
        nMarkerArray.push(nMarker); // Store nMarker in the array
        
        // Depending on the ID of the marker, get the corresponding 3D model.
        var root = getMatrixTransformNode(nMarker);

        // Get the marker matrix into the result matrix.
        detector.getTransformMatrix(i, resultMat);
        
        // Copy the marker matrix to the tmp matrix.
        var tmpMat = adaptMarkerMatrix(resultMat);
        console.error(tmpMat);
        // Copy the marker matrix over to your marker root object.
        root.setAttribute("matrix", tmpMat.toGL().toString());


        
    }

        setSwitchersVisibilityForArray(nMarkerArray, totalNumberModels);
}

/**
// Helper function to set visibility of switchers
function setSwitchersVisibility(choice, count) {
    for (var i = 0; i <= count; i++) {
        document.getElementById("switcher" + i).setAttribute("whichChoice", choice);
    }
}
*/

// Helper function to get the MatrixTransform node
function getMatrixTransformNode(nMarker) {
    var rootId = "root" + nMarker;
    return document.getElementById(rootId) || document.getElementById("root0");
}

// Helper function to set switchers visibility on only on the AR codes detected on camera
function setSwitchersVisibilityForArray(nMarkerArray, totalNumberModels) {
    for (var i = 0; i <= totalNumberModels; i++) {
        var choice = nMarkerArray.includes(i) ? 0 : -1;
        document.getElementById("switcher" + i).setAttribute("whichChoice", choice);
        if (choice === 0) {
            console.log('Number ' + i + ' found in array at position: ' + nMarkerArray.indexOf(i));
        }
    }
}

// Function to adapt the marker matrix
function adaptMarkerMatrix(arMat)
{
    var tmpMat = new x3dom.fields.SFMatrix4f(
        arMat.m00,  arMat.m01,  arMat.m02,  arMat.m03,
        arMat.m10,  arMat.m11,  arMat.m12,  arMat.m13,
        arMat.m20,  arMat.m21,  arMat.m22,  arMat.m23,
        0,          0,          0,          1);

    var translation = new x3dom.fields.SFVec3f(0,0,0),
        scale = new x3dom.fields.SFVec3f(1,1,1);
    var rotation = new x3dom.fields.Quaternion(0,0,1,0),
        scaleOrient = new x3dom.fields.Quaternion(0,0,1,0);

    tmpMat.getTransform(translation, rotation, scale, scaleOrient);

    // camera image is flipped, therefore flip orientation, too
    rotation.y *= -1;
    rotation.z *= -1;
    translation.y *= -1;
    translation.z *= -1;

    tmpMat = rotation.toMatrix();
    tmpMat.setTranslate(translation);

    return tmpMat;
}

// Function to initialize the tracker
function initializeTracker()
{
    // Setting up JSARToolKit
    canvas = document.createElement('canvas');
    canvas.id = "trackerCanvas";
    canvas.width = width;
    canvas.height = height;
    document.body.appendChild(canvas);

    if (DEBUG) { //shows the debug window
        var debugCanvas = document.createElement('canvas');
        debugCanvas.id = 'debugCanvas';
        debugCanvas.width = width;
        debugCanvas.height = height;
        document.body.appendChild(debugCanvas);
    }

    // Create an RGB raster object for the 2D canvas.
    // JSARToolKit uses raster objects to read image data.
    // Note that you need to set canvas.changed = true on every frame.
    raster = new NyARRgbRaster_Canvas2D(canvas);

    // FLARParam is the thing used by FLARToolKit to set camera parameters.
    // Here we create a FLARParam for images with 320x240 pixel dimensions.
    var param = new FLARParam(width, height);

    // The FLARMultiIdMarkerDetector is the actual detection engine for marker detection.
    // It detects multiple ID markers. ID markers are special markers that encode a number.
    detector = new FLARMultiIdMarkerDetector(param, 120);

    // For tracking video set continue mode to true. In continue mode, the detector
    // tracks markers across multiple frames.
    detector.setContinueMode(true);

    // Copy the camera perspective matrix from the FLARParam to the WebGL library camera matrix.
    // The second and third parameters determine the zNear and zFar planes for the perspective matrix.
    var camera = document.getElementById("vf");

    var zNear = camera.getNear();
    var zFar = camera.getFar();
    var perspectiveMatrix = runtime.projectionMatrix().toGL();

    param.copyCameraMatrix(perspectiveMatrix, zNear, zFar);

    var proj = new x3dom.fields.SFMatrix4f();
    proj.setFromArray(perspectiveMatrix);
    proj._22 *= -1;
    proj._32 *= -1;

    camera.setAttribute("projection", proj.toGL().toString());

    // Detecting markers
    videoCanvas = document.getElementById('bgnd');

    // Create a NyARTransMatResult object for getting the marker translation matrices.
    resultMat = new NyARTransMatResult();

    // Draw the video frame to the raster canvas, scaled to 320x240.
    // And tell the raster object that the underlying canvas has changed.
    redraw();
}

// Function to show the marker
function showMarker()
{
    var win = window.open('./marker.png','Marker','width=420,height=420');
    win.focus();
}
