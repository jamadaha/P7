#ifndef EntanglementEvaluatorModifiers_HH
#define EntanglementEvaluatorModifiers_HH

class EntanglementEvaluatorModifiers {
public:
	class LengthModifiers {
	public:
		static double Default(double length, double maxLength) {
			return length / maxLength;
		};
		static double LengthBias(double length, double maxLength) {
			return length * (length / maxLength);
		};
	};
	class OccuranceModifiers {
	public:
		static double Default(double occurance, double maxOccurance) {
			return occurance / maxOccurance;
		};
	};
};

#endif