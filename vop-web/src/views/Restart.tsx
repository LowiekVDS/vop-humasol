import Button from "../components/Button";
import { useEffect } from "react";
import { FormattedMessage } from "react-intl";
import ApiService from "../service/ApiService";

export default function Restart() {
  useEffect(() => {
    ApiService.fetch("/restart", "GET");
  }, []);

  return (
    <>
      <h1 className="text-4xl font-bold">
        <FormattedMessage id={"Restart!"} defaultMessage={"Restart"} />
      </h1>
      <p>
        <FormattedMessage
          id={"Wait until the restart is done!"}
          defaultMessage={"Wait until the restart is done!"}
        />
      </p>
      <Button className="mt-6" onClick={() => (window.location.href = "/")}>
        <FormattedMessage defaultMessage={"go back"} id={"go back"} />
      </Button>
    </>
  );
}
