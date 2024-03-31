const screen=document.querySelector(".screen");
const hours=document.querySelector(".hours");
const minutes=document.querySelector(".minutes");
const seconds=document.querySelector(".seconds");
const dateBar=document.querySelector(".date-bar")
const month = ["JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"];
function clock()
{
    const date=new Date();
    let dateDay=date.getDate();
    if(dateDay<10)
    {
        dateDay="0"+dateDay;
    }
    let dateYear=date.getFullYear();
    let dateHour=date.getHours();
    if(dateHour<10)
    {
        dateHour="0"+dateHour;
    }
    let dateMinutes=date.getMinutes();
    if(dateMinutes<10)
    {
        dateMinutes="0"+dateMinutes;
    }
    let dateSeconds=date.getSeconds();
    if(dateSeconds<10)
    {
        dateSeconds="0"+dateSeconds;
    }
    hours.innerText=dateHour;
    minutes.innerText=dateMinutes;
    seconds.innerText=dateSeconds;
    dateBar.innerText=dateDay + " " + month[date.getMonth()] + " " + dateYear;
    setTimeout(clock,1000);   
}

function innit()
{
    screen.addEventListener("load",clock());
    console.log("Clock is loaded.")
}

innit();




