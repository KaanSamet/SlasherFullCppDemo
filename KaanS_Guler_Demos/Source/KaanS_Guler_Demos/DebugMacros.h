#pragma once
#include "DrawDebugHelpers.h"

#define DRAWDEBUGSPHERE(Location) if (GetWorld()) DrawDebugSphere(GetWorld(), Location, 30.f, 24, FColor::Red, true);
#define DRAWDEBUGLINE(Location, Direction, Length) if (GetWorld()) DrawDebugLine(GetWorld(), Location, Location + Direction * Length, FColor::Red,true, -1.0f, 0, 1.f);
#define DRAWDEBUGPOINT(Location) if (GetWorld()) DrawDebugPoint(GetWorld(), Location, 10.f, FColor::Red, true);
#define DRAWVECTOR(LineStart, LineDirection, LineLength) if (GetWorld())\
	{ \
		DRAWDEBUGLINE(LineStart, LineDirection, LineLength)\
		DRAWDEBUGPOINT(LineStart)\
		DRAWDEBUGPOINT(LineStart + LineDirection * LineLength)\
	}

#define DRAWDEBUGSPHERE_ONEFRAME(Location) if (GetWorld()) DrawDebugSphere(GetWorld(), Location, 30.f, 24, FColor::Red, false, -1.f);
#define DRAWDEBUGLINE_ONEFRAME(Location, Direction, Length) if (GetWorld()) DrawDebugLine(GetWorld(), Location, Location + Direction * Length, FColor::Red, false, -1.0f, 0, 1.f);
#define DRAWDEBUGPOINT_ONEFRAME(Location) if (GetWorld()) DrawDebugPoint(GetWorld(), Location, 10.f, FColor::Red, false, -1.f);
#define DRAWVECTOR_ONEFRAME(LineStart, LineDirection, LineLength) if (GetWorld())\
	{ \
		DRAWDEBUGLINE_ONEFRAME(LineStart, LineDirection, LineLength)\
		DRAWDEBUGPOINT_ONEFRAME(LineStart)\
		DRAWDEBUGPOINT_ONEFRAME(LineStart + LineDirection * LineLength)\
	}
