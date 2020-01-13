#ifndef _MODEL
#define _MODEL

#include "core/layers.h"
#include <vector>

namespace NeuralNet {

	class Model {
		public:
			std::vector<Layer*> layers;
			void add_layer(Layer*);
			void compile();
			void dispose();
		private:
			bool compiled = false;
	};

}

#endif // !_MODEL