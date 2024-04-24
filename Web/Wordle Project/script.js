const ROUNDS=6;
const ANSWER_LENGTH=5;
const letters = document.querySelectorAll(".letter-box");
const msg=document.querySelector(".msg");

const API="https://words.dev-apis.com/word-of-the-day";
function isLetter(letter)
{
    return /^[a-zA-Z]$/.test(letter);
}







async function init()
{

    let currentRow=0;
    let currentGuess="";
    let done=false;
    let loading=true;
    
    const result=await fetch(API);
    const {word: wordRes} = await result.json();
    const correctWord=wordRes.toUpperCase(); 
    const correctWordLetters=correctWord.split("");//tworzy tablice liter ze słowa

    


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
            currentGuess=currentGuess.substring(0,currentGuess.length-1);
            letters[currentRow * ANSWER_LENGTH + currentGuess.length].innerText="";
        }
    }

    
    async function enter()
    {
        if(currentGuess.length<ANSWER_LENGTH)
        {}
        else
        {
            const res = await fetch("https://words.dev-apis.com/validate-word", {
            method: "POST",
            body: JSON.stringify({ word: currentGuess }),
            });
            const { validWord } = await res.json();
            
            if (!validWord) 
            {
                return;
            }

    
            currentGuess=currentGuess.toUpperCase();
            const guessParts=currentGuess.split("");
            let allRight=true;
            
            for(let i=0;i<ANSWER_LENGTH;i++)
            {
                if(guessParts[i]===correctWordLetters[i])
                {
                    letters[currentRow * ANSWER_LENGTH + i].classList.add("correct");
                }
                else
                {
                    allRight=false;
                    letters[currentRow * ANSWER_LENGTH + i].classList.add("wrong");
                    for(let j=0;j<ANSWER_LENGTH;j++)
                    {
                        if(guessParts[i]===correctWordLetters[j] && j!==i)
                        {
                            letters[currentRow * ANSWER_LENGTH + i].classList.replace('wrong','close');
                            break;
                        }
                    }
                }
            }
            currentRow++;
            currentGuess="";

            if(allRight)
            {
                msg.innerText="you win"
            }
            else if(currentRow===ROUNDS)
            {
                msg.innerText=`you lose\n the word was: ${correctWord}`
            }
        }
    }

    document.addEventListener("keydown", function handleKeyPress(event) {
        if(done || loading)
        {
            return;
        }
        const action = event.key;

        if (action === "Enter") 
        {
          enter();
        } 
        else if (action === "Backspace") 
        {
            backspace();
        } 
        else if (isLetter(action))
        {
            typeLetter(action);
        }
        else {}
    });
}

init();