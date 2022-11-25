#ifndef EVALUATIONMODIFIERS_HH
#define EVALUATIONMODIFIERS_HH

namespace JointPaths {
	class EvaluationModifiers {
	public:
		class LengthModifiers {
		public:
			static double None(double length, double maxLength) {
				return 1;
			};
			static double Default(double length, double maxLength) {
				return length / maxLength;
			};
			static double LengthBias(double length, double maxLength) {
				return (double)1 / std::max(maxLength - length, (double)1);
			};
		};
		class OccuranceModifiers {
		public:
			static double None(double occurance, double maxOccurance) {
				return 1;
			};
			static double Default(double occurance, double maxOccurance) {
				return occurance / maxOccurance;
			};
			static double LowOccuranceBias(double occurance, double maxOccurance) {
				return (double)1 / occurance;
			};
		};
	};

}

#endif