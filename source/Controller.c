/*
(CAT_DETECTED, MANUAL_INTERRUPTOR, PUMP_TIMER) -> (Encender Motor, Informar Display)
 
(LOW WATER LEVEL) -> (Encender LED, Informar Display)
*/
char[16] cat_name;

void Controller_init()
{

}

void Controller_setup(char * name)
{
cat_name = name;
}

void Controller_catDetected()
{
    //informar display
    WaterBomb_startPumping();
    delay_s(120);
    WaterBomb_stopPumping();
}

private void lowWaterLevel()

