$(function(){
    const labelRetorno = $("#labelRetorno");
    const btnLigar = $("#btnLigar");
    const btnDesligar = $("#btnDesligar");
    const request = function(params, callback = function(val){labelRetorno.html(val);}){
        $.post('php/controller.php', params, callback);
    }    

    btnLigar.click(function(){
        console.log("Enviado 'L'");
        request({led: "L"});
    });

    btnDesligar.click(function(){
        console.log("Enviado 'D'");
        request({led: "D"});
    });  
    
    setInterval(function(){
        console.log("Enviado 'R'");
        request({led: "R"});
    }, 2500);    
});