#ifndef STYLESHEET_H
#define STYLESHEET_H
#include <QString>
QString style("QPushButton:{
    background-color: #000;
    background-image: none;
border: 1px solid #000;
    border-radius: 4px;
    box-shadow: #fff 4px 4px 0 0,#000 4px 4px 0 1px;
    box-sizing: border-box;
color: #fff;
cursor: pointer;
display: inline-block;
    font-family: ITCAvantGardeStd-Bk,Arial,sans-serif;
    font-size: 14px;
    font-weight: 400;
    line-height: 20px;
margin: 0 5px 10px 0;
overflow: visible;
padding: 12px 40px;
    text-align: center;
    text-transform: none;
    touch-action: manipulation;
    user-select: none;
    -webkit-user-select: none;
    vertical-align: middle;
    white-space: nowrap;
}

.button-50:focus {
    text-decoration: none;
}

.button-50:hover {
    text-decoration: none;
}

.button-50:active {
    box-shadow: rgba(0, 0, 0, .125) 0 3px 5px inset;
outline: 0;
}

.button-50:not([disabled]):active {
    box-shadow: #fff 2px 2px 0 0, #000 2px 2px 0 1px;
transform: translate(2px, 2px);
}

@media (min-width: 768px) {
    .button-50 {
    padding: 12px 50px;
    }
}")
#endif // STYLESHEET_H
