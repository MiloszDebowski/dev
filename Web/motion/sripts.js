const popmotion = require('popmotion');
const ball = document.querySelector(".ball");

popmotion.animate({
    from: "0px",
    to: "20px",
    repeat: Infinity,
    repeatType: "reverse",
    type: "spring",
    onUpdate(update) {
        console.log(update);
        ball.style.top = update;
    }
});