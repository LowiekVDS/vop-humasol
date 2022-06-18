
export default class ApiService {

    static baseUrl = "http://192.168.0.109/api";

    static mock = false;

    static fetch = async (url, method: "GET" | "POST" | "PATCH", body: any = undefined) => {

        if (this.mock) {
            return {
                type: "Float Switch",
                password: "Qwerty123",
                LoS: false,
                distance: 400,
                txPower: 8,
                LoRaSpreadFactor: 10,
                bandwidth: 62.5
            }
        }

        return await fetch(`${this.baseUrl}${url}`, {
            method,
            body: body ? JSON.stringify(body) : undefined
        }).then(r => r.json());
    }
}