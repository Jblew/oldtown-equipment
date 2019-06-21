const sinusMin = 0.8;
const sinusMax = 1.0;
const radiansPerSecond = 0.1;

const fps = 1000 / 75;
const minFluorescent = 0.5;
const minRandom = 0.85;
const max = 0.9;
const fluorescentFlickerPercent = 0.985;

// static calc
const interval = 1000 / fps;
const radiansPerFrame = radiansPerSecond / fps;
const fullCircleRadians = 2 * Math.PI;


let sinRotationRadians = 0;

function flickeringAnimation(elem) {
    console.log(elem);
    var id = setInterval(frame, interval);

    function frame() {
        let brightness = max;

        sinRotationRadians += radiansPerFrame;
        if (sinRotationRadians > fullCircleRadians) sinRotationRadians -= fullCircleRadians;
        brightness = sinusMin + Math.sin(sinRotationRadians) * (sinusMax - sinusMin);

        if (Math.random() > fluorescentFlickerPercent) brightness *= minFluorescent;
        else brightness *= minRandom + Math.random() * (max - minRandom);

        let brightnessRaw = brightness * 50;
        elem.style.background = `hsl(182, 100%, ${brightnessRaw}%)`;
    }
}

$(document).ready(() => {
    flickeringAnimation(document.getElementById("field1"));
    flickeringAnimation(document.getElementById("field2"));
    flickeringAnimation(document.getElementById("field3"));
    console.log("Animation started");
});