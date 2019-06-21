function flickeringAnimation(elem) {
    console.log(elem);
    var id = setInterval(frame, 75);

    function frame() {
        const minFluorescent = 0.5;
        const minRandom = 0.85;
        const max = 0.9;
        const fluorescentFlickerPercent = 0.985;

        let brightness = max;

        let random = Math.random();
        if (random > fluorescentFlickerPercent) brightness = minFluorescent;
        else brightness = minRandom + Math.random() * (max - minRandom);

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