$(function(){
    const info = $("#info");
    const angulo = $("#angulo");
    const request = function(params, callback = function(val){console.log(val)}){
        $.post('php/controller.php', params, callback);
    }

    angulo.change(function(){
        let servo = this.value;
        if(servo == 0)
            servo = "a";
        else if(servo == 1)
            servo = "b";
        else if(servo == 2)
            servo = "c";
        else if(servo == 3)
            servo = "d";
        else if(servo == 4)
            servo = "e";
        request({servo});
    });

    setInterval(function(){
        request({servo: 1}, function(val){
            let servo = 0;
            switch(val){
                case "0°":
                    servo = 0;
                    break;
                case "45°":
                    servo = 1;
                    break;
                case "90°":
                    servo = 2;
                    break;
                case "135°":
                    servo = 3;
                    break;
                case "180°":
                    servo = 4;
                    break;
            }
            info.html("Ângulo do Servo: " + val);
            if(angulo.val() != servo)
                angulo.val(servo);            
        });
    }, 2500);
});