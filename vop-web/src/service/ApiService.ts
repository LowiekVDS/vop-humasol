
export default class ApiService {

    static baseUrl = "http://192.168.0.225/api";

    static fetch = async (url, method: "GET" | "POST" | "PATCH", body: any = undefined) => {
        return await fetch(`${this.baseUrl}${url}`, {
            method,
            body: body ? JSON.stringify(body) : undefined
        }).then(r => r.json());
    }
}