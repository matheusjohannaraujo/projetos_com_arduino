<?php

// Country: Brasil
// State: Pernambuco
// Developer: Matheus Johann Araújo
// Date: 2018-05-09

function streamSerial($value = 'R', $port = 'com2', $result = false, $bits = 9600, $iterator = 1){
    exec("mode $port: BAUD=$bits PARITY=N data=8 stop=1 xon=off");
    if(($conexao = @fopen($port, "w+") ?? false)){
        fwrite($conexao, $value);
        if($result){
            $result = fgets($conexao);
        }
        fclose($conexao);
    }else{
        if($iterator <= 5){
            sleep(5);
            return streamSerial($value, $port, $result, $bits, $iterator++);
        }
        $result = "Erro ao estabelcer conexão!";                
    }
    return $result;
}