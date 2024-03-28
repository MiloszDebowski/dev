const screen=document.querySelector(".screen");
let buffer="0";
let total=0;
let previousOperator;
let operationCount=0;
function keyClick(value)
{

    if(isNaN(parseInt(value)))
    {
        handleSymbol(value);
    }
    else
    {
        if(operationCount!==0)
        {
            buffer="0";
            operationCount=0;

        }
        handleNumber(value);
    }
    render();
}

function handleNumber(value)
{
    if(buffer==="0")
    {
        buffer=value;
    }
    else
    {
        buffer+=value;
    }
}

function handleMath(value)
{
    if(value===0)
    {
        return;
    }
    
    const intValue=parseInt(buffer);
    
    if(total===0)
    {
        total=intValue;
    }
    else
    {
        flush(intValue);
    }
    previousOperator=value;
    buffer="0";
}

function flush(intValue)
{
    if(previousOperator==="+")
    {
        total+=intValue;
    }
    else if(previousOperator==="-")
    {
        total-=intValue;
    }
    else if(previousOperator==="×")
    {
        total*=intValue;
    }
    else
    {
        total/=intValue;
    }
}

function handleSymbol(value)
{
    switch(value)
    {
        case "C":
            buffer="0";
            total=0;
            break;

        case "=":
            if(previousOperator===null)
            {
                return;
            }
            flush(parseInt(buffer));
            previousOperator=null;
            buffer= +total;
            total=0;
            operationCount++;
            break;
        
        case "←":
            if(buffer.length===1)
            {
                buffer="0";
            }
            else
            {
                buffer=buffer.substring(0,buffer.length-1);
            }
            break;
        case "+":
        case "-":
        case "÷":
        case "×":
            handleMath(value);
            break;
    }
}

function render()
{
    screen.innerText=buffer;
}

function init()
{
    document.querySelector(".keys").addEventListener("click",function(event){
        keyClick(event.target.innerText)
    });
}
init();