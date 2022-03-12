


class Layer {
    enum Type {
        PhysicalLayer,
    };
    public:
        Type type;
        const void* payload;
    public:
        Layer(Type type, const void* payload): type(type), payload(payload) {};
    public:
        
};