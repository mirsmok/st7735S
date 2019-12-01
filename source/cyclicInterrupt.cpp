void cyclicInterrupt(void)
{
//	static int i;
//	if(sig_num == SIGALRM)
//	{
//		i++;
//		if(i==10){ //execute every 1s 
			if(!roomSensor.error)
				roomSensor.timeoutTimer++;
			if(!outputModule.error)
				outputModule.timeoutTimer++;
			if(roomSensor.timeoutTimer > roomSensor.maxTimeout)
				roomSensor.error=true;
			if(outputModule.timeoutTimer > outputModule.maxTimeout)
				outputModule.error=true;
//			i=0;	
//		}
//	}
}
