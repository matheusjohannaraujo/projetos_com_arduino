$(function(){
    var lblRetorno = $("label#retorno");
    var btnLigar = $("button#btnLigar");
    var btnDesligar = $("button#btnDesligar");

    btnLigar.click(function(){
        console.log("L - Requisicao enviada");
        $.post('php/controller.php', {"led" : "L"}, function(retorno){
            lblRetorno.html(retorno);
        });
    });

    btnDesligar.click(function(){
        console.log("D - Requisicao enviada");
        $.post('php/controller.php', {"led" : "D"}, function(retorno){
            lblRetorno.html(retorno);
        });     
    });  
    
    setInterval(function(){
        console.log("R - Requisicao enviada");
        $.post('php/controller.php', {"led" : "R"}, function(retorno){
            lblRetorno.html(retorno);
        });
    }, 2500);    
});