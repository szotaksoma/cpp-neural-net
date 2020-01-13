#ifndef _MODEL
#define _MODEL

#include "layers.h"
#include <vector>

namespace NeuralNet {

	class Model {
		public:
			std::vector<Layer> layers;
			void add_layer(Layer);
			void build();
			void describe();
		private:
			bool compiled = false;
	};

}

#endif // !_MODEL