import "@ionic/react/css/core.css";
import { HashRouter, Route, Routes } from "react-router-dom";
import "./App.css";
import Header from "./components/Header";
import "./index.css";
import Configure from "./views/Configure";
import MainView from "./views/Main";
import Monitor from "./views/Monitor";
import PageNotFound from "./views/PageNotFound";
import Reset from "./views/Reset";
import Restart from "./views/Restart";

function App() {
  return (
    <div className="App">
      <Header />

      <div className="w-1/2 mx-auto mt-16 flex-grow grid text-center">
        <HashRouter>
          <Routes>
            <Route path="/" element={<MainView />} />
            <Route path="/monitor" element={<Monitor/>} />
            <Route path="/configure" element={<Configure/>} />
            <Route path="/reset" element={<Reset/>} />
            <Route path="/restart" element={<Restart/>} />
            <Route path="*" element={<PageNotFound />} />
          </Routes>
        </HashRouter>
      </div>
    </div>
  );
}

export default App;
