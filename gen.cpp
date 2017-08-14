#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<string.h>
#include<sstream.h>
#include<math.h>



float a=0.0 , b=0.0, stem=0.0 , thetamax=0.0, lambda,freq=0.0,gap=0.0;
const float Co=299792458.00;


int main()
{	
	clrscr();
	
	
	cout<<"\nEnter Frequency in MHz\t: ";
	cin>>freq;
	lambda=Co/(freq*1000000);
	cout<<"\nEnter value of the inner radius a in meters\t: ";
	cin>>a;
	float lb4=lambda/4;
	float base=lb4-stem;	
	cout<<"\nEnter value of the Stem in meters\t: ";
	cin>>stem;
	cout<<"\nEnter gap lenth at the capacitive termination\t:";
	cin>>gap;
	b=(1.5*0.055*lambda)-a;
	thetamax=atan((b-a)/(lb4-stem));
	if(b<=a)
		{
			cout<<"Warning!! Wrong value entered for inner radius. Should be less than 0.17 m\n";
			return -1;
		}
	ofstream  file;
	float theta=0.0;
	
	for(int i=0; i<500 ;i++)
	{
		if(theta<thetamax)
		{	
			float r= 0.1*stem ,r1=(cos(theta)/(1+cos(theta)))*(b-(a+base*tan(theta)));
			theta=i*0.002*thetamax;
			string filename;
			stringstream s;
			s<<i;		
			filename= "new_file_" + s.str();
			filename+=".af";
			/*cout<<filename<<endl;*/
			file.open(filename.c_str() , ios::out);
			file<<"frequency="<<freq<<" Angle= "<<theta*57.2957795<<" ThetaMax= "<<thetamax*57.2957795<<"\n"
			"&reg kprob=1,\n" 
			"conv=100.0 ,\n"            
			"icylin=1 ,\n"
			"freq="<<freq<<",\n"         
			"dx=.01,\n      "
			/*"xdri=0.0,ydri="<<(0.5*(a+b-base*tan(theta)))<<",\n"        */
			"norm=4,\n"
			"xnorm1="<<(lb4+0.5*a)<<",ynorm1="<<a<<",\n"
			"xnorm2="<<(lb4+0.5*a)<<",ynorm2="<<b<<",\n"
			"enorm=1000000.0, \n"
			"IRTYPE=1,\n"
			"TEMPK=2,\n"
			"beta=0.046&          \n"
			"&po x= "<<-r1*sin(theta)<<",  y= "<<r1*tan(theta)*sin(theta)+(a+base*tan(theta))<<" & \n"
			"&po x= 0.00,  y="<<b<<",nt=5,radius="<<r1<<"&\n"
			"&po x= "<<(lb4+gap-0.02*lb4)<<",  y= "<<b<<" &\n"
			"&po x="<<lb4+gap<<",y="<<b-(0.02*lb4)<<" ,nt=5, radius="<<(0.02*lb4)<<" &\n"
			"&po x= "<<lb4+gap<<",  y= 0.00 &\n"
			"&po x= "<<lb4<<",  y= 0.00 &\n"
			"&po x= "<<lb4<<",  y= "<<0.5*a<<"&\n"
			"&po x="<<(lb4-0.5*a)<<",y="<<a<<" ,nt=4, radius="<<(0.5*a)<<" &\n"
			"&po x= "<<(lb4-stem)<<",  y= "<<a<<"&\n"
			"&po x= "<<-r1*sin(theta)<<",  y= "<<r1*tan(theta)*sin(theta)+(a+base*tan(theta))<<" & \n";
		file.close();	
		}
		
		 		
		
	} 
}
