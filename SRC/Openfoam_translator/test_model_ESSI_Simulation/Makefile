
# Default Makefile Variables 
NP=4 

all: 
	 essi -f /home/hexiang/Dropbox/Research/current_work/Openfoam_translator/test_model_ESSI_Simulation/test_model_analysis.fei

serial: 
	 essi -f /home/hexiang/Dropbox/Research/current_work/Openfoam_translator/test_model_ESSI_Simulation/test_model_analysis.fei

parallel: 
	 mpirun -np ${NP} pessi -f /home/hexiang/Dropbox/Research/current_work/Openfoam_translator/test_model_ESSI_Simulation/test_model_analysis.fei

clean: 
	 rm *.feioutput 

