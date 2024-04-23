const ROUNDS=6;
const ANSWER_LENGTH=5;
const letters = document.querySelectorAll(".letter-box");

function isLetter(letter)
{
    return /^[a-zA-Z]$/.test(letter);
}







function init()
{

    let currentRow=0;
    let currentGuess="";
    let done=false;
    let loading=true;

    function typeLetter(letter)
    {
        if(currentGuess.length<ANSWER_LENGTH)
        {
            currentGuess+=letter;
        }
        else{}

        letters[currentRow * ANSWER_LENGTH + currentGuess.length -1].innerText=letter;
    }

    function backspace()
    {
        if(currentGuess!=="")
        {
            letters[currentRow * ANSWER_LENGTH + currentGuess.length -1].innerText=letter;
        }
    }

    function enter()
    {
        if(currentGuess.length<ANSWER_LENGTH)
        {}
        else
        {
            currentRow++;
            currentGuess="";
        }
    }

    document.addEventListener("keydown", function handleKeyPress(event) {

        const action = event.key;

        if (action === "Enter") 
        {
          console.log("enter");
          enter();
        } 
        else if (action === "Backspace") 
        {
            console.log("back")
            backspace();
        } 
        else if (isLetter(action))
        {
            console.log(action);
            typeLetter(action);
        
        }
        else {}
    });
}


init();