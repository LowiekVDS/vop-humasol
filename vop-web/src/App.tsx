import "@ionic/react/css/core.css";
import { HashRouter, Link, Route, Routes } from "react-router-dom";
import "./App.css";
import Header from "./components/Header";
import MainView from "./views/Main";
import PageNotFound from "./views/PageNotFound";

function App() {
  return (
    <div className="App">
      <Header />

      <HashRouter>
        <Routes>
          <Route path="/" element={<MainView/>} />
          <Route path="*" element={<PageNotFound/>} />
        </Routes>
      </HashRouter>
    </div>
  );
}

export default App;
