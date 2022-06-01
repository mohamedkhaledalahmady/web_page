const btn_1 = document.getElementById("13");
const btn_2 = document.getElementById("12");
const btn_3 = document.getElementById("11");
const btn_4 = document.getElementById("10");

btn_1.style.backgroundColor = 'black';
btn_1.style.color = 'red';

btn_2.style.backgroundColor = 'black';
btn_2.style.color = 'green';

btn_3.style.backgroundColor = 'black';
btn_3.style.color = 'blue';

btn_4.style.backgroundColor = 'black';
btn_4.style.color = 'yellow';

let count_1 = 0;
btn_1.addEventListener('click', function(){
    count_1 = count_1 == 10 ? 0 : count_1 + 1;
    if(count_1 % 2 == 1)      // mean led on 
    {   
        btn_1.style.backgroundColor = 'red';
        btn_1.style.color = 'white';
    }
    else
    {
        btn_1.style.backgroundColor = 'black';
        btn_1.style.color = 'red';
    }
})

let count_2 = 0;
btn_2.addEventListener('click', function(){
    count_2 = count_2 == 10 ? 0 : count_2 + 1;
    if(count_2 % 2 == 1)      // mean led on 
    {   
        btn_2.style.backgroundColor = 'green';
        btn_2.style.color = 'white';
    }
    else
    {
        btn_2.style.backgroundColor = 'black';
        btn_2.style.color = 'green';
    }
})

let count_3 = 0;
btn_3.addEventListener('click', function(){
    count_3 = count_3 == 10 ? 0 : count_3 + 1;
    if(count_3 % 2 == 1)      // mean led on 
    {   
        btn_3.style.backgroundColor = 'blue';
        btn_3.style.color = 'white';
    }
    else
    {
        btn_3.style.backgroundColor = 'black';
        btn_3.style.color = 'blue';
    }
})

let count_4 = 0;
btn_4.addEventListener('click', function(){
    count_4 = count_4 == 10 ? 0 : count_4 + 1;
    if(count_4 % 2 == 1)      // mean led on 
    {   
        btn_4.style.backgroundColor = 'yellow';
        btn_4.style.color = 'black';
    }
    else
    {
        btn_4.style.backgroundColor = 'black';
        btn_4.style.color = 'yellow';
    }
})