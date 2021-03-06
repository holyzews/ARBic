/* Author:  Zhenjia Wang Dec. 22, 2014
 * Usage: This is part of bicluster package. Use, redistribution, modify without limitations
 * show how does the whole program work
 */

/***********************************************************************/

#include "main.h"
#include<iostream>
/***********************************************************************/

int main(int argc, char* argv[])
{
	/* Start the timer */
	uglyTime(NULL);
	printf("\nARBic %.1f: greedy biclustering (compiled %s %s)\n\n", VER, __DATE__, __TIME__);
	rows = cols = 0;

	/* get the program options defined in get_options.c */
	get_options(argc, argv);
	
	/*get the size of input expression matrix*/
	get_matrix_size(po->FP);	
	progress("File %s contains %d genes by %d conditions", po -> FN, rows, cols);
	if (rows < 4 || cols < 4)
	{
		/*neither rows number nor cols number can be too small*/
		errAbort("Not enough genes or conditions to make inference");
	}
	genes = alloc2c(rows, LABEL_LEN);
	conds = alloc2c(cols, LABEL_LEN);
//我想可以在这里加if else 分开两个算法
switch(po->MODE)
{

	case 1: {
	
	if(po->DIVIDED2 != 0)
	{
		po->DIVIDED = po->DIVIDED2;
	}
//lxy g
	else
	{
			po->DIVIDED = cols; 
	
	}
	if(po->QUANTILE2 < 0.00001)
	{	
			po->QUANTILE = 0.5;
	}
	else{
		po->QUANTILE = po->QUANTILE2;
	}

	/* Read in the gene names and condition names */
	read_labels(po -> FP);	

    	/* Read in the expression data */
	if (po->IS_DISCRETE)
		read_discrete(po -> FP);
	else
	{	/*real data preprocessing*/
		read_continuous(po -> FP);
		if(po->density>0)
		{
    		discretize_Density();
		}
		else{
    		if(po->dataMode==1){
			
    			//partitionMapping();//lxy g
    			discretize(addSuffix(po->FN,".rules"));
    		}/*simulated data preprocessing*/
    		else{
		
    			if(po->QUANTILE>=0.5)
    				discretizeSq();
    			else
    				discretizeS(addSuffix(po->FN,".rules"));
    		}
		}
		
	}
	fclose(po->FP);
//std::cout<<"00"<<std::endl;	
	/*read in the sub-gene list*/
	if (po->IS_list)
	{
		sub_genes = alloc2c(rows, LABEL_LEN);
		read_list (po->FL);
	}
	/*we can do expansion by activate po->IS_SWITCH*/
	if (po->IS_SWITCH)
	{
		read_and_solve_blocks(po->FB, addSuffix(po->BN,".expansion"));
	}
	else
	{
		/* formatted file */
		write_imported(addSuffix(po->FN,".chars"));
	
		/* the file that stores all blocks */
		if (po->IS_list)
			//make_graph((char *)(addSuffix((char *)(addSuffix((char *)(po->FN), (char *)(po->LN))), (char *)".block")));
			{
			colbased(addSuffix(addSuffix(po->FN, po->LN),".cblock"));
			}
			
		else
			//make_graph((char *)(addSuffix((char *)(po->FN), (char *)".blocks")));
			{
			colbased(addSuffix(po->FN,".cblocks"));
			}
   	 }
   	 break;
	}
	case 2:
	{
		if(po->DIVIDED2 != 0)
		po->DIVIDED = po->DIVIDED2;
	else{
		if(rows>2000)
			po->DIVIDED = 15;
		else
			po->DIVIDED = cols; 
			
	}
	if(po->QUANTILE2 < 0.00001)
	{	
		if(rows<=2000)
			po->QUANTILE = 0.5;
		else
			po->QUANTILE = ((int)(15.0/(cols*1.0)*100+0.5))/100.0;
	}
	else{
		po->QUANTILE = po->QUANTILE2;
	}
	/* Read in the gene names and condition names */
	read_labels(po -> FP);	

    	/* Read in the expression data */
	if (po->IS_DISCRETE)
		read_discrete(po -> FP);
	else
	{	/*real data preprocessing*/
		read_continuous(po -> FP);
		if(po->density>0)
		{
    		discretize_Density();
		}
		else{
    		if(po->dataMode==1){
			
    			//partitionMapping();//lxy g
    			discretize(addSuffix(po->FN,".rules"));
    		}/*simulated data preprocessing*/
    		else{
		
    			if(po->QUANTILE>=0.5)
    				discretizeSq();
    			else
    				discretizeS(addSuffix(po->FN,".rules"));
    		}
		}
		
	}
	fclose(po->FP);
	
	/*read in the sub-gene list*/
	if (po->IS_list)
	{
		sub_genes = alloc2c(rows, LABEL_LEN);
		read_list (po->FL);
	}

	/*we can do expansion by activate po->IS_SWITCH*/
	if (po->IS_SWITCH)
	{
		read_and_solve_blocks(po->FB, addSuffix(po->BN, ".expansion"));
	}
	else
	{
		/* formatted file */
		write_imported(addSuffix(po->FN, ".chars"));
	
		/* the file that stores all blocks */
		if (po->IS_list)
			make_graph(addSuffix(addSuffix(po->FN, po->LN),".block"));
		else		
			make_graph(addSuffix(po->FN, ".blocks"));

   	}
   	break;
	}
	/*
	case 3:
	{
	if(po->DIVIDED2 != 0)
	{
		po->DIVIDED = po->DIVIDED2;
	}

	else
	{
			po->DIVIDED = cols; 
	
	}
	if(po->QUANTILE2 < 0.00001)
	{	
			po->QUANTILE = 0.5;
	}
	else{
		po->QUANTILE = po->QUANTILE2;
	}

	// Read in the gene names and condition names 
	read_labels(po -> FP);	

    	// Read in the expression data 
	if (po->IS_DISCRETE)
		read_discrete(po -> FP);
	else
	{	//real data preprocessing
		read_continuous(po -> FP);
		if(po->dataMode==1){
			
			//partitionMapping();//lxy g
			discretize(addSuffix(po->FN,".rules"));
		}//simulated data preprocessing
		else{
		
			if(po->QUANTILE>=0.5)
				discretizeSq();
			else
				discretizeS(addSuffix(po->FN,".rules"));
		}
	}
	fclose(po->FP);
//std::cout<<"00"<<std::endl;	
	//read in the sub-gene list
	if (po->IS_list)
	{
		sub_genes = alloc2c(rows, LABEL_LEN);
		read_list (po->FL);
	}
	//we can do expansion by activate po->IS_SWITCH
	if (po->IS_SWITCH)
	{
		read_and_solve_blocks(po->FB, addSuffix(po->BN,".expansion"));
	}
	else
	{
		// formatted file 
		write_imported(addSuffix(po->FN,".chars"));
	
		//the file that stores all blocks 
		if (po->IS_list)
			{			
			colbased(addSuffix(addSuffix(po->FN, po->LN),".cblock"));
			make_graph((char *)(addSuffix((char *)(addSuffix((char *)(po->FN), (char *)(po->LN))), (char *)".block")));
			}
			
		else
			{
			colbased(addSuffix(po->FN,".cblocks"));
			make_graph((char *)(addSuffix((char *)(po->FN), (char *)".blocks")));
			}
   	 }
   	 break;
	} */
	}  	 
	free(po);
	free (sublist);
	return 0;
}

/***********************************************************************/
