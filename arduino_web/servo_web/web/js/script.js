function req(params, callback = function(){}){
    $.post('php/controller.php', params, callback);
}

$(function(){
    var lblRetorno = $("#retorno");
    var angulo = $("#angulo");

    angulo.change(function(){
        let x = this.value;
        if(x == 0)
            x = "a";
        else if(x == 1)
            x = "b";
        else if(x == 2)
            x = "c";
        else if(x == 3)
            x = "d";
        else if(x == 4)
            x = "e";
        req({x});
    });

    setInterval(function(){
        req({x: 1}, function(retorno){
            x = 0;
            switch(retorno){
                case "0°":
                    x = 0;
                    break;
                case "45°":
                    x = 1;
                    break;
                case "90°":
                    x = 2;
                    break;
                case "135°":
                    x = 3;
                    break;
                case "180°":
                    x = 4;
                    break;
            }
            lblRetorno.html("Ângulo do Servo: " + retorno);
            if(angulo.val() != x)
                angulo.val(x);            
        });
    }, 2500);
});