<?php
    session_start();
    
    if(!isset($_SESSION['requisicao'])){
        $_SESSION['requisicao'] = "Off";
    }

    //var_dump($_REQUEST);

    if(($led = $_REQUEST['led'] ?? false) && ($_SESSION['requisicao'] == "Off")){
        $_SESSION['requisicao'] = "On";
        /*LINUX e MAC
        $port = '/dev/ttyUSB0';*/

        /*WINDOWS*/
        $port = 'com2';
        exec("mode ".$port.": BAUD=9600 PARITY=N data=8 stop=1 xon=off");        

        if($arduino = @fopen($port, "w+") ?? false){
            switch($led){
                case "On":
                    fwrite($arduino, 'L');
                    echo "<br>";
                    echo fgets($arduino);
                    break;
                case "Off":
                    fwrite($arduino, 'D');
                    echo "<br>";
                    echo fgets($arduino);
                    break;
            }
            @fclose($arduino);
        }
        $_SESSION['requisicao'] = "Off";
    }
?>