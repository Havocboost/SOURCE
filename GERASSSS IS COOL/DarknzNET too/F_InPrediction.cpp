#include "main.h"

bool __fastcall C_Interface::InPrediction(void *thisptr, int edx)
{
	bool inPrediction = Interface->Prediction()->GetOriginalMethod<InPrediction_t>(INDEX_INPREDICTION)(thisptr);


	return inPrediction;
}