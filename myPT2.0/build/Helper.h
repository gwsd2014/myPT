
class Helper{
	private:
		static int nextID;
	public:
		static int nextTextureID(){
			nextID++;
			return nextID;
		}
};

int Helper::nextID = 0;