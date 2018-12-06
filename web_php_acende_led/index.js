"use strict";
$(function(){
    var lblRetorno = $("label#retorno");
    var btnLigar = $("button#btnLigar");
    var btnDesligar = $("button#btnDesligar");

    btnLigar.click(function(){
        if(confirm("Deseja ligar o LED?")){
            console.log("A - Requisicao enviada");
            $.post('./arduino.php', {"led" : "On"}, function(retorno){
                lblRetorno.html(retorno);
            });
        }
    });

    btnDesligar.click(function(){
        if(confirm("Deseja desligar o LED?")){
            console.log("B - Requisicao enviada");
            $.post('./arduino.php', {"led" : "Off"}, function(retorno){
                lblRetorno.html(retorno);
            });
        }        
    });    
});